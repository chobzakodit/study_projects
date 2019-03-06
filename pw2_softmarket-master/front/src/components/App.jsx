import React, { Component } from 'react';
import Routers from 'routers'
import { BrowserRouter } from 'react-router-dom';
import { connect } from "react-redux";
import { bindActionCreators } from 'redux'
import { categoriesActions, productsActions, cartActions } from 'store/actions'
import { categoriesApi, productsApi, cartApi } from 'api'
import { withStyles } from '@material-ui/core/styles';
import './App.css';

const styles = theme =>({

})

class App extends Component {
  constructor(props){
    super(props)
    this.state={

    }
  }
  componentDidMount(){
    const {setCartCount} = this.props
    cartApi.getCartCount((error,data) => {
      if(error) return console.error(error)
      console.log(data)
      setCartCount(data.count)      
    })
  }
  render() {
    return (
      <BrowserRouter>
        <Routers/>
      </BrowserRouter>
    );
  }
}

const mapStateToProps = state => ({
  cart:state.cart
})
const mapDispatchToProps = dispatch => bindActionCreators(cartActions,dispatch)

export default withStyles(styles)(connect(mapStateToProps,mapDispatchToProps)(App))
