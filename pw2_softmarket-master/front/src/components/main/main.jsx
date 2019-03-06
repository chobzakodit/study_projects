import React, { Component } from 'react'
import {Sidebar,Breakpoints, Banner,ShopList} from 'components'
import {Grid} from '@material-ui/core'
import {withStyles} from '@material-ui/core/styles'
import { connect } from "react-redux";
import { bindActionCreators } from 'redux'
import { categoriesActions, productsActions } from 'store/actions'
import { categoriesApi, productsApi } from 'api'

const styles = theme => ({
  root:{
  }
})


class Main extends Component {
  constructor(props){
    super(props)
    this.state={
    }
  }
  componentDidMount(){
    const {setCategories,setProducts} = this.props    
    categoriesApi.getCategories((error,data)=>{
      if(error) return console.error("getCategories-Error: ",error)
      console.log("getCategories-Data: ",data)  
      setCategories({
        list:data,
        totalCount:0,
      })    
    })
    productsApi.getAllProducts((error,data) => {
      if(error) return console.error("getAllitems-Error: ", error) 
      console.log("getAllitems-Data: ",data)  
      setProducts({
        list:data,
        totalCount:data.length,
      })         
    })
  }
  render() {
    const {classes,products,categories} = this.props;
    return (
      <section className={classes.root}>
        <Breakpoints title={"ShopingList"}/>
        <Grid container >
          <Grid item sm={4} md={3} xs={12}>
            <Sidebar categories={categories}/>
          </Grid>
          <Grid item sm={8} md={9} xs={12}>
            <Banner/>
            <ShopList products={products}/>
          </Grid>
        </Grid>
      </section>
    )
  }
}
const mapStateToProps = state => ({
  categories: state.categories,
  products: state.products
})
const mapDispatchToProps = dispatch => bindActionCreators(
  {
    ...categoriesActions,
    ...productsActions
  },dispatch)


export default withStyles(styles)(connect(mapStateToProps,mapDispatchToProps)(Main))