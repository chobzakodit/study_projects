import {SERVER} from 'config'

export const getCategories = (cb) => { 

  fetch(SERVER+'/api/categories',{
    method:'get',
    mode:'cors'
  })
  .then(res => res.json())
  .then(data => cb(null,data))
  .catch(error => cb(error))
}