import React from 'react';

var FontAwesome = require('react-fontawesome');

function ProjectList(props) {

    const projectClicked = project => evt => {
        props.projectClicked(project);
    }

    const editClicked = project => {
        props.editClicked(project);
    }

    const removeClicked = project => {
        fetch(`${process.env.REACT_APP_API_URL}/api/projects/${project.id}/`, {
            method: 'DELETE',
            headers: {
                'Authorization': 'Token 48f70e1b25d0a31ea4c8ef0b90dcebff1d0ea0f7',
                'Content-Type': 'application/json',
            },
            }).then( resp => props.projectDeleted(project))
            .catch( error => console.log(error))
    }

    const newProject = () => {
        props.newProject();
    }

    return (
        <div>
            { props.projects.map( project => {
                return (
                    <div key={project.id} className="project-item">
                        <h2 className="project-name" onClick={projectClicked(project)}>
                            {project.name}
                        </h2>
                    <FontAwesome name="edit" onClick={() => editClicked(project)} />
                    <FontAwesome name="trash" onClick={() => removeClicked(project)}/>
                    </div>
                )
            })}
            <button onClick={newProject}>Add Project</button>
        </div>
    )
}

export default ProjectList;