<?php

namespace App\Http\Controllers;
use App\Category;
use App\Article;
use Illuminate\Support\Facades\DB;

class ArticleController extends Controller
{
    public static function getArticlesByCategory($category_id){
        $categories = Category::getAllCategoriesById($category_id);
        $articles = Article::select('name','category','price','avalaible')
								->whereIn('category',$categories)
                                ->get();
        return response()->json($articles);
    }
    public static function getAll(){
        return Article::select('id','name','category','image_path','price','avalaible')
                        ->get();
    }
}
?>