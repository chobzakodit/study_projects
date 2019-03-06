import categoriesReducer from './categoriesReducer'
import productsReducer from './productsReducer'
import cartReducers from './cartReducers'
import {combineReducers} from 'redux'

export default combineReducers({
    categories:categoriesReducer,
    products:productsReducer,
    cart:cartReducers,
})