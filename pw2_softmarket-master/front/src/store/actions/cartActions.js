import {cartConst} from '../consts'

export const setCartCount = (count) => ({
    type:cartConst.SET_COUNT,
    payload:{
        totalCount:count,
    }
})
export const setCart = (props) => ({
    type:cartConst.SET_LIST,
    payload:{
        totalCount:props.totalCount,
        list:props.list,
        price:props.price,
    }
})