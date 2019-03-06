import React, { Component } from 'react'
import {Typography} from '@material-ui/core'
import {withStyles} from '@material-ui/core/styles'

const styles = theme => ({
  root:{
    width:"100%",
    height: 0,
    paddingBottom: '23%',
    backgroundColor:"#c7c7c7",
    // border:"1px solid #000",
    borderRadius:"4px",
    marginBottom:15,
    position:"relative"
  },
  titleBox:{
    position:"absolute",
    width:"100%",
    height:"auto",
    left:"3%",
    bottom:"5%",
  },
  title:{
    color:"#ffffff",
    fontWeight:300,
    [theme.breakpoints.down('sm')]:{
      fontSize:35,
      color:"red"
    },
    [theme.breakpoints.down('xs')]:{
      fontSize:25,
      color:"blue"
    },
    
  }
})


class Banner extends Component {
  render() {
    const {classes} = this.props;
    return (
      <div className={classes.root}>
        <div className={classes.titleBox}>
          <Typography variant="h3" className={classes.title}>Banner</Typography>
          <Typography variant="h3" className={classes.title}>880 x 208px</Typography>
        </div>
      </div>
    )
  }
}
export default withStyles(styles)(Banner)