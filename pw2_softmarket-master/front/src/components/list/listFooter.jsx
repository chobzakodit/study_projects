import React, { Component } from 'react'
import {Typography, Button,Fab} from '@material-ui/core'
import {withStyles} from '@material-ui/core/styles'

const styles = theme => ({
  root:{
    width:"100%",
    display:'flex',
    justifyContent:"center",
    margin:"20px 5px"
  },
  btn:{
    margin:"20px 8px",
    width:"auto",
    minWidth: "40px",
    boxShadow:"none",
  }
})


class ListFooter extends Component {
  constructor(props){
    super(props)
  }
  prevPage = () => { 
    const {classes,page, changePage} = this.props
    if(page>0)
      return (
        <Fab variant="extended" className={classes.btn} size="small" onClick={() => changePage(page-1)}>PrevPage</Fab>
      )
  }
  nextPage = () => {
    const {classes,page, changePage, pages} = this.props
    if(page<pages-1)
    return (
      <Fab variant="extended" className={classes.btn} size="small" onClick={() => changePage(page+1)}>NextPage</Fab>
    )

  }
  totalPage = () => {
    const {pages} = this.props
    const _pages = []
    for (let i = 0; i < pages; i++) {
      _pages.push(i)      
    }
    return _pages
  }
  render() {
    const {classes,changePage, page} = this.props;
    return (
      <div className={classes.root}>
        {this.prevPage()}
        {this.totalPage().map(item => {
          return <Fab 
            className={classes.btn}
            key={item} 
            color={item === page ? "primary" : "default"}
            onClick={() => changePage(item)} 
            size="small">
              {item+1}
          </Fab>
        })}
        {this.nextPage()}

      </div>
    )
  }
}
export default withStyles(styles)(ListFooter)