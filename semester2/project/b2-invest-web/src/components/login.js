import React, { Component } from 'react';
import { withCookies } from 'react-cookie';

class Login extends Component {
    // TODO: Registration with selection `who are you`?
    // investor, entrepreneur or expert
    state = {
        credentials: {
            username: '',
            password: '',
        },
        error_text: '',
    }

    inputChanged = event => {
        let cred = this.state.credentials
        cred[event.target.name] = event.target.value;
        this.setState({credentials: cred})
    }

    login = event => {
        console.log(this.state.credentials);
        fetch(`${process.env.REACT_APP_API_URL}/auth/`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(this.state.credentials)
            }).then( resp => resp.json())
            .then( res => {
                if('non_field_errors' in res)
                    this.setState({error_text: res['non_field_errors'][0]});
                else {
                    this.setState({error_text: ''});
                    console.log(res.token);
                    window.location.href = "/main";
                    this.props.cookies.set('b2invest-token', res.token)
                }
            })
            .catch( error => {
                console.log(error);
            })
    }

    render() {
        return <div className="login-container">
            <h1>Login</h1>
            {this.state.error_text ? <span className="error">{this.state.error_text}<br/> </span>: <span></span>}
            <span>Username</span><br />
                <input type="text" name="username" value={this.state.credentials.username}
                    onChange={this.inputChanged} /><br />
            <span>Password</span><br />
                <input type="password" name="password" value={this.state.credentials.password}
                    onChange={this.inputChanged} /><br />

            <button onClick={this.login}>Login</button>
        </div>
    }
}

export default withCookies(Login);