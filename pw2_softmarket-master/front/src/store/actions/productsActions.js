import {productsConst} from '../consts'

export const setProducts = (props) => ({
    type:productsConst.SET_LIST,
    payload:{
        list:props.list,
        totalCount:props.totalCount
    }
})