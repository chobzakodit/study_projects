import React, { Component } from 'react'
import {Grid, Typography} from '@material-ui/core'
import {Breakpoints} from 'components'
import {withStyles} from '@material-ui/core/styles'
import { connect } from "react-redux";
import { bindActionCreators } from 'redux'
import { cartApi, productsApi } from 'api'
import { cartActions } from 'store/actions'
import TableCart from './table'
import OrderCart from './order'

const styles = theme => ({
  root:{
  }
})


class Cart extends Component {
  constructor(props){
    super(props)
    this.state={
      list:[]
    }
  }
  componentDidMount(){
    const {setCartCount} = this.props
    productsApi.getProductsByCategory({id:5},(error,data) => {
      if(error) return console.error("cart.getProductsByCategory-Error: ",error)
      console.log("cart.getProductsByCategory-Error: ",data)
      this.setState({list:data})

    })
    cartApi.getCartCount((error,data) => {
      if(error) return console.error("cart.getCartCount-Error: ",error)
      console.log("cart.getCartCount-Error: ",data)
      setCartCount(data.count)      
    })

  }
  render() {
    const {classes,cart} = this.props;
    return (
      <section className={classes.root}>
        <Breakpoints title={"ShopingCart"}/>
        {/* <Typography variant="h1">{cart.totalCount === 0 ? "TUT PUSTO =(" : "TUT ROVNO "+cart.totalCount}</Typography> */}
        <TableCart list={this.state.list}/>
        {/* <OrderCart/> */}

      </section>
    )
  }
}
const mapStateToProps = state => ({
  cart:state.cart
})
const mapDispatchToProps = dispatch => bindActionCreators(cartActions,dispatch)

export default withStyles(styles)(connect(mapStateToProps,mapDispatchToProps)(Cart))