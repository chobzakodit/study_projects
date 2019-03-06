<?php

use Illuminate\Http\Request;
use App\Http\Controllers\CategoryController as Cc;
use App\Http\Controllers\ArticleController as Ac;
use App\Http\Controllers\CartController as CartC;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

Route::middleware(['web'])->group(function() use($router){
	Route::group(['prefix' => 'products'], function () use ($router) {
		Route::get('/',  function () {
			return Ac::getAll();
		});
		Route::get('/{category_id}',  function ($category_id) {
			return Ac::getArticlesByCategory($category_id);
		});
	});
	Route::group(['prefix' => 'categories'], function () use ($router) {
		Route::get('/',  function () {
			return Cc::getList();
		});
	});
	Route::group(['prefix' => 'cart',], function () use ($router) {
		Route::get('/count',  function (Request $request) {
			return CartC::count($request);
		});
		Route::post('/add_article',  function (Request $request) {
			return CartC::addToCart($request);
		});
		Route::post('/remove_article',  function (Request $request) {
			return CartC::removeFromCart($request);
		});
		Route::get('/get_cart',  function (Request $request) {
			return CartC::getAll($request);
		});
	});
});