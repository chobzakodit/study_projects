import {SERVER} from 'config'

export const getCart = (cb) => { 

  fetch(SERVER+'/api/cart',{
    method:'get',
    mode:'cors'
  })
  .then(res => res.json())
  .then(data => cb(null,data))
  .catch(error => cb(error))
}

export const getCartCount = (cb) => { 

  fetch(SERVER+'/api/cart/count',{
    method:'get',
    mode:'cors'
  })
  .then(res => res.json())
  .then(data => cb(null,data))
  .catch(error => cb(error))
}
export const addToCart = (data, cb) => {

	fetch(SERVER + '/api/cart/add_article', {
			method: 'POST',
			mode: 'cors',
			body: 'article_id=' + data.id,
			headers: new Headers({
				'Content-Type': 'application/x-www-form-urlencoded', // <-- Specifying the Content-Type
			}),
		})
		.then(res => res.json())
		.then(data => cb(null, data))
		.catch(error => cb(error))
}