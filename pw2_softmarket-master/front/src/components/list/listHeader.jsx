import React, { Component } from 'react'
import ReactDOM from 'react-dom';
import { Typography, FormControl, InputLabel, Select, Input, MenuItem,Button,Menu } from '@material-ui/core'
import { withStyles } from '@material-ui/core/styles'
import { ArrowUpward, ExpandMore } from '@material-ui/icons'

const styles = theme => ({
	root: {
		width: "100%",
		display: "flex",
		justifyContent: "space-between",
		alignItems: "center",
		padding: 10,
	},
	title: {

	},
	btns: {

	},
	btn:{
		border:"solid 2px #eaeaea",
		borderRadius:"25px",
		marginLeft:10,
		padding:"6px 16px",
		fontSize:12,
		fontWeight:300,
		textTransform: 'none',
		minWidth:34,

	}
})


class ListHeader extends Component {
	constructor(props) {
		super(props)
		this.state = {
			perPageMenu:null,
			positionMenu:null,
		}
	}
	handleChange = event => {
		const { changePerPage } = this.props;
		console.log(event.target)
		switch (event.target.title) {
			case "perPage":
				changePerPage(event.target.value)
				break;
			default:
				break;
		}
		
		this.handleClose()

	};
	handleClick = event => {
		console.log(this.refs)		
		switch (event.target.name) {
			case "perPage":
				this.setState({ perPageMenu: event.currentTarget });				
				break;
			case "position":
				this.setState({ positionMenu: event.currentTarget });				
				break;		
			default:
				break;
		}
	};
	handleClose = () => {		
		this.setState({ positionMenu: null, perPageMenu:null });
	};
	menus = () => {
		const { perPageMenu, positionMenu } = this.state;
		return (<div>
			<Menu
				name="perPage"
				anchorEl={perPageMenu}
				open={Boolean(perPageMenu)}
				onClose={this.handleClose}
			>
				<MenuItem onClick={this.handleChange} value={5}	title="perPage">5 Per page</MenuItem>
				<MenuItem onClick={this.handleChange} value={10} title="perPage">10 Per page</MenuItem>
				<MenuItem onClick={this.handleChange} value={15} title="perPage">15 Per page</MenuItem>
			</Menu>
			<Menu
				name="position"
				anchorEl={positionMenu}
				open={Boolean(positionMenu)}
				onClose={this.handleClose}
			>
				<MenuItem onClick={this.handleChange} value={"pip"} title="position">Pip</MenuItem>
				<MenuItem onClick={this.handleChange} value={"pop"} title="position">Pop</MenuItem>
			</Menu>
		</div>)
	}
	render() {
		const { classes, perPage } = this.props;
		const { anchorEl } = this.state;
		return (
			<div className={classes.root}>
				<div className={classes.title}>
					<Typography variant="caption">150 item(s)</Typography>
				</div>
				<div className={classes.btns}>
					<Button
						// aria-owns={anchorEl ? 'perPage' : undefined}
						name="perPage"
						ref="perPageBtn"
						aria-haspopup="true"
						onClick={this.handleClick}
						className={classes.btn}
						variant="outlined"
						size="small"
					>{perPage} PerPage<ExpandMore style={{fontSize:14}}/></Button>
					<Button
						name="position"
						aria-haspopup="true"
						onClick={this.handleClick}
						className={classes.btn}
						variant="outlined"
						size="small"
					>Position<ExpandMore style={{fontSize:14}}/></Button>
					<Button
						name="actionUp"
						aria-haspopup="true"
						onClick={this.handleClick}
						className={classes.btn}
						variant="outlined"
						size="small"
						style={{padding:6}}
					><ArrowUpward style={{fontSize:14}}/></Button>
					{this.menus()}


				</div>
			</div>
		)
	}
}
export default withStyles(styles)(ListHeader)