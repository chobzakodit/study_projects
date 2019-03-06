import React,{Fragment} from 'react';
import ReactDOM from 'react-dom';
import {App} from 'components';
import CssBaseline from '@material-ui/core/CssBaseline';
import { createStore } from "redux";
import { Provider } from "react-redux";
import { Reducers } from "./store";

const store = createStore(
    Reducers,
    window.__REDUX_DEVTOOLS_EXTENSION__ && window.__REDUX_DEVTOOLS_EXTENSION__()
)

ReactDOM.render(
    <Provider store={store}>
        <CssBaseline />
        <App />
    </Provider>
    ,document.getElementById('root')
);
