<?php

namespace App\Http\Controllers;
use App\Category;
use App\Article;
use Illuminate\Support\Facades\DB;

class CategoryController extends Controller
{
	 /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        //
    }
    public static function getCategoryContent($path){
		$content = Category::select('id','name','path','count')
								->where('path','rlike',"^".$path.".[0-9]$")
								->get();
		if(!empty($content)){
			foreach($content as $c){
				$c->categories=self::getCategoryContent($c['path']);
			}
		}
		return $content;
	}		
	public static function getList(){
		self::countProductsCategories();
		$categories = Category::select('id','name','path','count')
								->where('path','rlike','^[0-9]$')
								->get();
		foreach($categories as $cat){
			$cat->categories=self::getCategoryContent($cat['path']);
		}
    	return response()->json($categories);
	}
	//Function counting available products for one category
	//will be called every time after updating of "articles" table
	public static function countProducts($catname){
		$count= Article::where('category','like',$catname)
						->count();
		return $count;
	}
	//Function counting available for every category
	public static function countProductsCategories(){
		$categories = Category::select('id','name','count')
								->get();
		foreach($categories as $cat){
			$count=self::countProducts($cat['name']);
			Category::where('id',$cat['id'])
					->update(['count'=>$count]);
		}					
	}
}