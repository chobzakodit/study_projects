import React, { Component } from 'react'
import {Grid, Typography} from '@material-ui/core'
import {Breakpoints} from 'components'
import {withStyles} from '@material-ui/core/styles'
import { connect } from "react-redux";
import { bindActionCreators } from 'redux'

const styles = theme => ({
  root:{
  }
})


class OrderCart extends Component {
  constructor(props){
    super(props)
    this.state={

    }
  }
  componentDidMount(){
  }
  render() {
    const {classes} = this.props;
    return (
      <div className={classes.root}>
        <Typography variant="h5">OrderCart</Typography>
      </div>
    )
  }
}
const mapStateToProps = state => ({
    
})
const mapDispatchToProps = dispatch => ({})

export default withStyles(styles)(connect(mapStateToProps,mapDispatchToProps)(OrderCart))