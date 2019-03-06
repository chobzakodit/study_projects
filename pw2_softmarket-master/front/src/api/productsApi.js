import {
	SERVER
} from 'config'

export const getAllProducts = (cb) => {

	fetch(SERVER + '/api/products', {
			method: 'get',
			mode: 'cors'
		})
		.then(res => res.json())
		.then(data => cb(null, data))
		.catch(error => cb(error))
}

export const getProductsByCategory = (data, cb) => {

	fetch(SERVER + '/api/products/' + data.id, {
			method: 'GET',
			mode: 'cors',
			// body:'article_id='+data.id,
		})
		.then(res => res.json())
		.then(data => cb(null, data))
		.catch(error => cb(error))
}
