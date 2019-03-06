import React, { Component } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux';
import { withStyles } from '@material-ui/core/styles';
import { Header, Footer, Main} from 'components'

const styles = theme =>({
  root:{
    
  }
})

class HomePage extends Component {
  constructor(props) {
    super(props)
  }

  render() {
    return (
      <div className="App">
        <Header />
        <hr />
        <Main />
        <Footer />
      </div>
    )
  }
}

export default withStyles(styles)(connect(
  state => ({
  }),
  dispatch => ({})
)(HomePage))