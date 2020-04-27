import React, { Component } from 'react';
import './App.css';
import ProjectList from './components/project-list';
import ProjectDetails from './components/project-details';
import ProjectFrom from './components/project-form';

class App extends Component {

  state = {
    projects: [],
    selectedProject: null,
    editedProject: null
  }

  componentDidMount() {
    //fetch data
    fetch(`${process.env.REACT_APP_API_URL}/api/projects/`, {
      method: 'GET',
      headers: {
        'Authorization': 'Token 48f70e1b25d0a31ea4c8ef0b90dcebff1d0ea0f7',
      }
    }).then( resp => resp.json())
    .then( res => this.setState({projects: res}))
    .catch( error => console.log(error))
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

  render(){
    return (
      <div className="App">
          <h1>B2Invest</h1>
          <div className="layout">
            <ProjectList projects={this.state.projects} projectClicked={this.loadProject}
              projectDeleted={this.projectDeleted} editClicked={this.editClicked} 
              newProject={this.newProject}/>
            <div>
              { !this.state.editedProject ? 
                <ProjectDetails project={this.state.selectedProject} updateProject={this.loadProject}/>
                : <ProjectFrom project={this.state.editedProject} cancelForm={this.cancelForm} />}
            </div> 
          </div>
      </div>
    );
  }
}

export default App;
