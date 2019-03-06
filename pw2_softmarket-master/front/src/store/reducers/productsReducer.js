import {productsConst} from '../consts'

const defaultState = {
    list:[],
    totalCount:0
}

export default (state = defaultState, action = {}) => {
    switch(action.type){
        case productsConst.SET_LIST:{
            
            const result = {
                list:action.payload.list,
                totalCount:action.payload.totalCount,
            }
            return result
        }
        default: return state
    }
}