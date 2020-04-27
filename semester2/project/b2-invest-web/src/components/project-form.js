import React, { Component } from 'react';

import Checkbox from './checkbox';

class ProjectForm extends Component {

    state = {
        editedProject: this.props.project,
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
            console.log('changed');
        }
    }

    updateChecked = () => {
        let categories = this.state.categories;
        categories.forEach(category => {
            category.isChecked = this.props.project.categories.indexOf(category.value) !== -1;           
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
        console.log(project)
        this.setState({categories: categories})
        this.setState({editedProject: project})
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
            .then( res => console.log(res))
            .catch( error => console.log(error))
    }

    updateClicked = () => {
        console.log(this.state.editedProject);
    }

    render() {
        return (
            <React.Fragment>
                <span>Name</span><br />
                <input type="text" name="name" value={this.props.project.name}
                    onChange={this.inputChanged} /><br />
                <span>Description</span><br />
                <textarea name="description" value={this.props.project.description} 
                    onChange={this.inputChanged} /><br />

                <span>Capital</span><br />
                <input type="number" name="capital" value={this.props.project.capital}
                    onChange={this.inputChanged} /><br />

                {/* <span>Categories</span><br /> */}
                {/* <input type="checkbox" name="categories[]" value={this.props.project.categories[0]} checked={1}
                    onChange={this.inputChanged} />Category 1<br />

                <input type="checkbox" name="categories[]" value={this.props.project.categories[1]} checked={this.props.project.categories.indexOf(2) !== -1}
                    onChange={this.inputChanged} />Category 2<br />

                <input type="checkbox" name="categories[]" value={this.props.project.categories[2]} checked={this.props.project.categories.indexOf(3) !== -1}
                    onChange={this.inputChanged} />Category 3<br /> */}

                {this.state.categories.map(item => (
                    <label key={item.key}>
                    {item.label}
                    <Checkbox name={item.name} value={item.value} checked={item.isChecked} onChange={this.checkboxChanged} />
                    <br /></label>
                ))}

                <span>Entrepreneur</span><br />
                <input type="number" name="entrepreneur" value={this.props.project.entrepreneur}
                    onChange={this.inputChanged} /><br />
                {/* check if exist project or we just creating it */}
                {!this.props.project.id ? 
                <button onClick={this.saveClicked}>Save</button> :
                <button onClick={this.updateClicked}>Update</button>}
                
                <button onClick={this.cancelClicked}>Cancel</button>
            </React.Fragment>
        )
    }
}

export default ProjectForm;