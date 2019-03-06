import React, { Component } from 'react'
import {Typography, Grid} from '@material-ui/core'
import {withStyles} from '@material-ui/core/styles'
import img1 from './img1.png'
import img2 from './img2.png'
import img3 from './img3.png'
import img4 from './img4.png'

const styles = theme => ({
  root:{
    width:"100%",
    margin:"20px 0"
  },
  img:{
    width:"100%",
    heigh:"auto"
  }
})


class MainFooter extends Component {
  render() {
    const {classes} = this.props;
    return (
      <div className={classes.root}>
        <Grid container spacing={24}>
          <Grid item xs={12} sm={6} md={3}><img className={classes.img} src={img1} alt=""/></Grid>
          <Grid item xs={12} sm={6} md={3}><img className={classes.img} src={img2} alt=""/></Grid>
          <Grid item xs={12} sm={6} md={3}><img className={classes.img} src={img3} alt=""/></Grid>
          <Grid item xs={12} sm={6} md={3}><img className={classes.img} src={img4} alt=""/></Grid>
        </Grid>
        
      </div>
    )
  }
}
export default withStyles(styles)(MainFooter)