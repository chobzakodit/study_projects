import React, { Component } from 'react'
import { withStyles } from '@material-ui/core/styles';
import { Typography, TextField, InputAdornment } from '@material-ui/core';
import {ArrowDropDown, Search} from '@material-ui/icons/';
import logo from './logo.png'
import {Link} from 'react-router-dom'
import { connect } from "react-redux";
import { bindActionCreators } from 'redux'

const styles = theme => ({
  root: {
    // backgroundColor: 'red',
    marginTop:10,
    marginBottom:10,
  },
  top:{
    display:'flex',
    marginBottom:15,
  },
  top_rigth_a:{
    padding:'5px 7px',
    marginLeft:7,
  },  
  main:{
    display:'flex',
    margin:'20px 0'
  },
  logo:{
    marginTop:-5
  },
  nav:{
    flexGrow:1,
    textAlign:'right'
  },
  nav_li:{
    listStyle:"none",
    display:'inline-block',
    padding:'0px 5px'
  },
  nav_li_a:{
    color:'#8c8c8c !important', 
    fontSize:14,
    padding:'5px 10px',
    '&:hover':{
      color:'#222222 !important'
    }
  }, 
  search_box:{
    marginLeft:20,
  },
  search:{
  },
  search_input:{
    padding:8,
    borderColor: '#419cdf',
  },
  search_input_label:{
    transform: "translate(14px, 10px) scale(1)"
  },
});

class header extends Component {
  constructor(props){
    super(props)
    this.state = {
      nav :[
        'office',
        'multimedia',
        'design',
        'developer',
        'utilites',
        'games'
      ]
    }
  }
  render() {
    const {classes, cart} = this.props
    return (
      <section className={classes.root}>
        <div className={classes.top}>
          <Typography variant="caption" style={{flexGrow:1}}>
            Shop by Phone <span style={{fontWeight:900}}>(01) 123 456 SM</span> <a href="#" >Live Chat With Us</a>
          </Typography>
          <Typography variant="caption"  align="right">
            <a href="#"  className={classes.top_rigth_a}>My Account</a>
            <a href="#"   style={{borderRight:"solid 1px #eaeaea", paddingRight:5}}><ArrowDropDown fontSize="small" style={{verticalAlign:"middle"}}/></a>
            <Link to="/cart"  className={classes.top_rigth_a}>My Cart {cart.totalCount !== 0 ? '('+cart.totalCount+')' : ''}</Link>
            <a href="#"   style={{borderRight:"solid 1px #eaeaea", paddingRight:5}}><ArrowDropDown fontSize="small" style={{verticalAlign:"middle"}}/></a>
          </Typography>

        </div>
        <div className={classes.main}>
          <div className={classes.logo}>
            <Link to="/"><img src={logo} alt=""/></Link>
          </div>
          <nav className={classes.nav}>
            {this.state.nav.map(item => (
              <li className={classes.nav_li} key={item}><Typography variant="overline"><a href="#" className={classes.nav_li_a}>{item}</a></Typography></li>
            ))}
          </nav>
          <div className={classes.search_box}>
            <TextField
              id="input-search"
              label="Search"
              className={classes.search}              
              type="text"
              name="search"
              autoComplete="search"
              variant="outlined"

              InputLabelProps={{
                classes: {
                  root: classes.search_input_label,
                },
              }}

              InputProps={{
                classes: {
                  input: classes.search_input,
                },
                endAdornment: (
                  <InputAdornment position="start">
                    <Search   />
                  </InputAdornment>
                ),
              }}
              
            />
          </div>
        </div>
      </section>
    )
  }
}
const mapStateToProps = state => ({
  cart:state.cart
})
const mapDispatchToProps = dispatch => ({})

export default withStyles(styles)(connect(mapStateToProps,mapDispatchToProps)(header))