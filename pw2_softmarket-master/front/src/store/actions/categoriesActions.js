import {categoriesConst} from '../consts'

export const setCategories = (props) => ({
    type:categoriesConst.SET_LIST,
    payload:{
        list:props.list,
        totalCount:props.totalCount
    }
})