import React, { Component, Fragment } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux';
import { withStyles } from '@material-ui/core/styles';
import { Header, Footer, Cart} from 'components'


const styles = theme => ({
    root: {
    },
});

class CartPage extends Component {
  constructor(props){
    super(props)
  }
  
  render() {
    const {classes } = this.props
    
    return (
      <div className="App">
        <Header />
        <hr />
        <Cart/>
        <Footer />
      </div>
    )
  }
}

const mapStateToProps = state => ({
})
const mapDispatchToProps = dispatch => ({})

export default withStyles(styles)(connect(mapStateToProps,mapDispatchToProps)(CartPage))