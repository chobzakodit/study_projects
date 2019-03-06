import {cartConst} from '../consts'

const defaultState = {
    totalCount:0,
    list:[],
    price:0,
}

export default (state = defaultState, action = {}) => {
    switch(action.type){
        case cartConst.SET_LIST:{
            const {totalCount,list,price} = action.payload
            
            const result = {
                list,
                totalCount,
                price,
            }
            return result
        }
        case cartConst.SET_COUNT:{
            
            const {totalCount} = action.payload
            const result = {
                list:[],
                price:0,
                totalCount
            }
            return result
        }
        default: return state
    }
}