import React, { Component } from 'react';
var FontAwesome = require('react-fontawesome');

class ProjectDetails extends Component {

    state = {
        highlighted: -1
    }

    highlightedRate = high => evt => {
        this.setState({highlighted: high});
    }

    rateClicked = stars => evt => {
        fetch(`${process.env.REACT_APP_API_URL}/api/projects/${this.props.project.id}/rate_project/`, {
        method: 'POST',
        headers: {
            'Authorization': 'Token 48f70e1b25d0a31ea4c8ef0b90dcebff1d0ea0f7',
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({stars: stars})
        }).then( resp => resp.json())
        .then( res => this.getDetails())
        .catch( error => console.log(error))
    }

    getDetails = () => {
        fetch(`${process.env.REACT_APP_API_URL}/api/projects/${this.props.project.id}/`, {
        method: 'GET',
        headers: {
            'Authorization': 'Token 48f70e1b25d0a31ea4c8ef0b90dcebff1d0ea0f7',
            'Content-Type': 'application/json',
        },
        }).then( resp => resp.json())
        .then( res => this.props.updateProject(res))
        .catch( error => console.log(error))
    }
    
    render() {
        const proj = this.props.project;

        return (
            <React.Fragment>
            { this.props.project ? (
                <div>
                    <h3>{this.props.project.name}</h3>
                    <FontAwesome name="star" className={proj.avg_rating > 0 ? 'orange': ''} />
                    <FontAwesome name="star" className={proj.avg_rating > 1 ? 'orange': ''} />
                    <FontAwesome name="star" className={proj.avg_rating > 2 ? 'orange': ''} />
                    <FontAwesome name="star" className={proj.avg_rating > 3 ? 'orange': ''} />
                    <FontAwesome name="star" className={proj.avg_rating > 4 ? 'orange': ''} />
                    ({proj.no_of_ratings})
                    <p>{proj.description}</p>

                    <div className="rate-container">
                        <h2>Rate this project!</h2>
                        { [...Array(5)].map( (event, index) => {
                            return <FontAwesome key={index} name="star" className={this.state.highlighted > index - 1 ? 'purple': ''} 
                                onMouseEnter={this.highlightedRate(index)} onMouseLeave={this.highlightedRate(-1)} onClick={this.rateClicked(index + 1)}/>
                        })}
                    </div>
                </div>
            ) : null}
            </React.Fragment>
        )
    }
}

export default ProjectDetails;