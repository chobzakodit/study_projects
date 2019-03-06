import React from 'react'
import {Route, Switch} from 'react-router-dom';
import {HomePage, CartPage} from 'pages'

export default (props) => (
    <Switch>
        <Route exact path="/"  component={HomePage}/>
        <Route path="/cart" component={CartPage} />
        <Route component={HomePage}/>
    </Switch>
)