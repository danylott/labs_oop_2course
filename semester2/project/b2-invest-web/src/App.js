import React, { Component } from 'react';
import './App.css';

var FontAwesome = require('react-fontawesome');

class App extends Component {

  render(){
    return (
      <div className="App">
          <h1>
            <span>B2Invest</span>
            <FontAwesome name="briefcase"/>
          </h1>
      </div>
    );
  }
}

export default App;
