import React, { Component } from 'react';
import { withCookies } from 'react-cookie';

import './../App.css';
import ProjectList from './project-list';
import ProjectDetails from './project-details';
import ProjectFrom from './project-form';

var FontAwesome = require('react-fontawesome');

class ProjectAdmin extends Component {

  state = {
    projects: [],
    selectedProject: null,
    editedProject: null,
    token: this.props.cookies.get('b2invest-token'),
  }

  componentDidMount() {
    if(this.state.token) {
      fetch(`${process.env.REACT_APP_API_URL}/api/projects/`, {
        method: 'GET',
        headers: {
          'Authorization': `Token ${this.state.token}`,
        }
      }).then( resp => resp.json())
      .then( res => this.setState({projects: res}))
      .catch( error => console.log(error))
    } else {
      window.location.href = '/';
    }
  }

  replaceProject = project => {
    let projects = this.state.projects;
    let index = projects.findIndex(proj => proj.id === project.id);
    projects[index] = project;
    this.setState({projects: projects, selectedProject: project, editedProject: null})
  }

  loadProject = project => {
    this.setState({selectedProject: project, editedProject: null})
  }

  projectDeleted = selProject => {
    const projects = this.state.projects.filter( project => project.id !== selProject.id)
    this.setState({projects: projects, selectedProject: null})
  }

  editClicked = selProject => {
    this.setState({editedProject: selProject});
  }

  newProject = () => {
    this.setState({editedProject: {name: '', description: '', capital: 1,
    categories: [], entrepreneur: 1}})
  }

  cancelForm = () => {
    this.setState({editedProject: null})
  }

  addProject = project => {
    this.setState({projects: [...this.state.projects, project]})
  }

  render(){
    return (
      <div className="App">
          <h1>
            <span>B2Invest</span>
            <FontAwesome name="briefcase"/>
          </h1>
          <div className="layout">
            <ProjectList token={this.state.token} projects={this.state.projects} projectClicked={this.loadProject}
              projectDeleted={this.projectDeleted} editClicked={this.editClicked} 
              newProject={this.newProject}/>
            <div>
              { !this.state.editedProject ? 
                <ProjectDetails token={this.state.token} project={this.state.selectedProject} updateProject={this.loadProject}/>
                : <ProjectFrom token={this.state.token} project={this.state.editedProject} cancelForm={this.cancelForm} 
                  newProject={this.addProject} editProject={this.replaceProject}/>}
            </div> 
          </div>
      </div>
    );
  }
}

export default withCookies(ProjectAdmin);
