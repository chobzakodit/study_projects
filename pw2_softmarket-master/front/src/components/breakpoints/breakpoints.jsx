import React, { Component } from 'react'
import {Typography} from '@material-ui/core'
import {withStyles} from '@material-ui/core/styles'

const styles = theme => ({
  root:{
    marginTop:15,
    marginBottom:15,
  }
})

class Breakpoints extends Component {
  render() {
    const {classes, title} = this.props;
    return (
      <div className={classes.root}>
      <Typography variant="caption">Home > {title}</Typography>
      <Typography variant="h4">{title}</Typography>
        
      </div>
    )
  }
}
export default withStyles(styles)(Breakpoints)