import React, { Component } from 'react';

import Checkbox from './checkbox';

class ProjectForm extends Component {

    state = {
        editedProject: {...this.props.project},
        categories: [
            {
              name: 'categories',
              value: 1,
              key: 'Category 1',
              label: 'Category 1',
              isChecked: this.props.project.categories.indexOf(1) !== -1
            },
            {
              name: 'categories',
              value: 2,
              key: 'Category 2',
              label: 'Category 2',
              isChecked: this.props.project.categories.indexOf(2) !== -1
            },
            {
              name: 'categories',
              value: 3,
              key: 'Category 3',
              label: 'Category 3',
              isChecked: this.props.project.categories.indexOf(3) !== -1
            },
        ]
    }

    componentDidUpdate(prevProps) {
        if (prevProps !== this.props) {
            this.updateChecked();
            this.setState({editedProject: {...this.props.project},})
            console.log('changed');
        }
    }

    updateChecked = () => {
        let categories = this.state.categories;
        categories.forEach(category => {
            category.isChecked = this.state.editedProject.categories.indexOf(category.value) !== -1;           
        })
        this.setState({categories: categories})
    }

    cancelClicked = () => {
        this.props.cancelForm();
    }

    inputChanged = event => {
        let project = this.state.editedProject
        project[event.target.name] = event.target.value;
        this.setState({editedProject: project})
    }

    checkboxChanged = event => {
        let categories = this.state.categories;
        let project = this.state.editedProject
        categories.forEach(category => {
        if (category.value == event.target.value) {
            
            category.isChecked = event.target.checked;
            const index = project.categories.indexOf(category.value)
            if(event.target.checked && index === -1) {
                project.categories.push(category.value)
            }
            else
            if(!event.target.checked && index > -1) {
                project.categories.splice(index, 1);
            }
        }   
        })
        this.setState({categories: categories, editedProject: project})
    }
    
    saveClicked = () => {
        console.log(this.state.editedProject);
        fetch(`${process.env.REACT_APP_API_URL}/api/projects/`, {
            method: 'POST',
            headers: {
                'Authorization': 'Token 48f70e1b25d0a31ea4c8ef0b90dcebff1d0ea0f7',
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(this.state.editedProject)
            }).then( resp => resp.json())
            .then( res => this.props.newProject(res))
            .catch( error => console.log(error))
    }

    updateClicked = () => {
        fetch(`${process.env.REACT_APP_API_URL}/api/projects/${this.props.project.id}/`, {
            method: 'PUT',
            headers: {
                'Authorization': 'Token 48f70e1b25d0a31ea4c8ef0b90dcebff1d0ea0f7',
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(this.state.editedProject)
            }).then( resp => resp.json())
            .then( res => this.props.editProject(res))
            .catch( error => console.log(error))
    }

    // TODO: make information non-static
    render() {

        const isDisabled = this.state.editedProject.name.length === 0 ||
            this.state.editedProject.description.length === 0 ||
            this.state.editedProject.categories.length === 0;

        return (
            <React.Fragment>
                <span>Name</span><br />
                <input type="text" name="name" value={this.state.editedProject.name}
                    onChange={this.inputChanged} /><br />
                <span>Description</span><br />
                <textarea name="description" value={this.state.editedProject.description} 
                    onChange={this.inputChanged} /><br />

                <span>Capital</span><br />
                <input type="number" name="capital" value={this.state.editedProject.capital}
                    onChange={this.inputChanged} /><br />
                
                <span>Categories</span>
                <ul>
                {this.state.categories.map(item => (
                    <li key={item.key}>
                        <label>
                        {item.label}
                        <Checkbox name={item.name} value={item.value} checked={item.isChecked} onChange={this.checkboxChanged} />
                        <br /></label>
                    </li>
                ))}
                </ul>

                <span>Entrepreneur</span><br />
                <input type="number" name="entrepreneur" value={this.state.editedProject.entrepreneur}
                    onChange={this.inputChanged} /><br />
                {/* check if exist project or we just creating it */}
                {!this.props.project.id ? 
                <button disabled={isDisabled} onClick={this.saveClicked}>Save</button> :
                <button disabled={isDisabled} onClick={this.updateClicked}>Update</button>}
                
                <button onClick={this.cancelClicked}>Cancel</button>
            </React.Fragment>
        )
    }
}

export default ProjectForm;