import React, { Component } from 'react';
import './App.css';
import ProjectList from './components/project-list';

class App extends Component {

  state = {
    projects: []
  }

  componentDidMount() {
    //fetch data
    fetch('http://127.0.0.1:8000/api/projects/', {
      method: 'GET',
      headers: {
        'Authorization': 'Token 48f70e1b25d0a31ea4c8ef0b90dcebff1d0ea0f7',
      }
    }).then( resp => resp.json())
    .then( res => this.setState({projects: res}))
    .catch( error => console.log(error))
  }

  render(){
    return (
      <div className="App">
          <h1>B2Invest</h1>
          <ProjectList projects={this.state.projects} />
      </div>
    );
  }
}

export default App;
