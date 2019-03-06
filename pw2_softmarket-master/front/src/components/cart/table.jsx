import React, { Component } from 'react'
import { Grid, Typography, Table, TableBody, TableCell, TableFooter, TableHead, TableRow, Fab, Paper } from '@material-ui/core'
import { Breakpoints } from 'components'
import { withStyles } from '@material-ui/core/styles'
import { connect } from "react-redux";
import { bindActionCreators } from 'redux'

const styles = theme => ({
	root: {
	},
	btnDelete: {
		width: 38,
		height: 38,
		boxShadow: "none"
	},
	col_name:{
		display:"flex",
		alignItems:"center",
		fontSize:"16px",
		cursor:"pointer",
		color:"#419cdf "
	},
	img:{
		margin:"10px"
	}
})


class TableCart extends Component {
	constructor(props) {
		super(props)
		this.state = {
		}
	}
	componentDidMount() {
	}
	render() {
		const { classes, list } = this.props;
		return (
			<div className={classes.root}>
				<Paper>
					<Table className={classes.table}>
						<TableHead>
							<TableRow>
								<TableCell>Item Name</TableCell>
								<TableCell>Price</TableCell>
								<TableCell>Quantity</TableCell>
								<TableCell>Subtotal</TableCell>
								<TableCell >Delete</TableCell>
							</TableRow>
						</TableHead>
						<TableBody>
							{list.map(item => {
								const count = 1;
								const subtotal = count * item.price;
								return (
									<TableRow key={item.id}>
										<TableCell component="th" scope="row">
											<div  className={classes.col_name} >
												<img className={classes.img} src="http://placehold.it/70x90/" />{item.name}

											</div>
										</TableCell>
										<TableCell >{item.price}</TableCell>
										<TableCell>{count}</TableCell>
										<TableCell >{subtotal}</TableCell>
										<TableCell ><Fab className={classes.btnDelete} size="small">x</Fab></TableCell>
									</TableRow>
								);
							})}
						</TableBody>
					</Table>
				</Paper>
			</div>
		)
	}
}
const mapStateToProps = state => ({
})
const mapDispatchToProps = dispatch => ({})

export default withStyles(styles)(connect(mapStateToProps, mapDispatchToProps)(TableCart))