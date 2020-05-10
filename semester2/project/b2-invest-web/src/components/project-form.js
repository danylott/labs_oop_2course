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
            //   isChecked: this.props.project.categories.indexOf(1) !== -1
            },
            {
              name: 'categories',
              value: 2,
              key: 'Category 2',
              label: 'Category 2',
            //   isChecked: this.props.project.categories.indexOf(2) !== -1
            },
            {
              name: 'categories',
              value: 3,
              key: 'Category 3',
              label: 'Category 3',
            //   isChecked: this.props.project.categories.indexOf(3) !== -1
            },
        ]
    }

    componentDidMount() {
        this.populateCategoriesCheckboxes();
        console.log(this.props.capitals);
        console.log(this.props.categories);
    }

    componentDidUpdate(prevProps) {
        if (prevProps !== this.props) {
            this.setState({editedProject: {...this.props.project}})
            this.updateChecked();
            this.updateSelected();
            console.log('changed');
            // console.log(this.state.editedProject)
        }
    }

    populateCategoriesCheckboxes = () => {
        let categories = this.props.categories;
        let checkboxes = []
        categories.forEach(category => {
            checkboxes.push(
                {
                    name: "categories",
                    value: category.id,
                    key: category.name,
                    label: category.name,
                    isChecked: this.props.project.categories.indexOf(category.id) !== -1,
                }
            )
        })
        this.setState({categories: checkboxes})
    }

    updateChecked = () => {
        let categories = this.state.categories;
        categories.forEach(category => {
            category.isChecked = this.props.project.categories.indexOf(category.value) !== -1;           
        })
        this.setState({categories: categories})
    }

    updateSelected = () => {
        let select = document.getElementById("capital");
        for(let i, j = 0; i = select.options[j]; j++) {
            if(i.value == this.props.project.capital) {
                select.selectedIndex = j;
                break;
            }
        }
        console.log(select);
    }

    cancelClicked = () => {
        this.props.cancelForm();
    }

    inputChanged = event => {
        let project = this.state.editedProject
        project[event.target.name] = event.target.value;
        this.setState({editedProject: project});
        // console.log(this.state.editedProject);
    }

    selectChanged = event => {
        let project = this.state.editedProject;
        project[event.target.name] = Number(event.target.value);
        this.setState({editedProject: project});
        console.log(this.state.editedProject);
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
        this.setState({categories: categories, editedProject: project});
    }
    
    saveClicked = () => {
        fetch(`${process.env.REACT_APP_API_URL}/api/projects/`, {
            method: 'POST',
            headers: {
                'Authorization': `Token ${this.props.token}`,
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
                'Authorization': `Token ${this.props.token}`,
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
                <select defaultValue={this.props.project.capital} name="capital" id="capital" onChange={this.selectChanged}>
                {this.props.capitals.map(item => (
                    <option key={item.id} value={item.id}>{item.name}</option>
                ))}
                </select>

                
                
                <span>Categories</span>
                <ul>
                {this.state.categories.map(item => (
                    <li key={item.key}>
                        <label className="category-label">
                        {item.label}
                        <span className="category-checkbox">
                        <Checkbox name={item.name} value={item.value} checked={item.isChecked} onChange={this.checkboxChanged} />
                        </span>
                        <br />
                        </label>
                    </li>
                ))}
                </ul>

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