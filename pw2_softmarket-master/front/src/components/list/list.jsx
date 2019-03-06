import React, { Component } from 'react'
import { Typography, Grid } from '@material-ui/core'
import { withStyles } from '@material-ui/core/styles'
import HeaderList from './listHeader'
import FooterList from './listFooter'
import Product from './item'

const styles = theme => ({
	root: {
		width: "100%",
		// border:"1px solid #000",
		minHeight: "100px",
	},
})


class ShopList extends Component {
	constructor(props) {
		super(props)
		this.state={
			perPage:5,
			page:0,
			pages:1,
		}
	}
	changePerPage = perPage =>{
		this.setState({perPage})		
	}
	changePage = page =>{
		this.setState({page})
	}
	viewList = (list, startIndex, count) => {
		const result = []
		for (let i = startIndex; i < startIndex+count; i++) {
			result.push(list[i])					
		}
		
		return result;
	}
	render() {
		const { classes,products } = this.props;
		const { perPage,page,pages } = this.state;
		const {list} = products
		const {length} = list;
		let startIndex, viewCount = 0;
		if(length < perPage){
			startIndex = 0
			viewCount = length
		}
		else {
			startIndex = page * perPage
			if(length - page * perPage <= perPage) {
				viewCount = length - page * perPage
			}else{				
				viewCount = perPage
			}
		}
		return (
			<div className={classes.root}>
				<HeaderList perPage={perPage} changePerPage={this.changePerPage}/>
				<hr />
				<Grid container spacing={24}>					
					{this.viewList(list,startIndex,viewCount).map(item => (
						<Grid item xs={12} sm={6} md={4} key={item.id}> 
							<Product item={item} />
						</Grid>
					))}
				</Grid>
				<FooterList page={page} pages={length/perPage} changePage={this.changePage}/>
			</div>
		)
	}
}
export default withStyles(styles)(ShopList)