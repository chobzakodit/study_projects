<?php

namespace App\Http\Controllers;

use Illuminate\Support\Facades\DB;
use Illuminate\Http\Request;
use App\Article;

class CartController extends Controller
{
    public static function count(Request $request){
        if($request->session()->has('cart_count'))
            return response()->json(['count'=>$request->session()->get('cart_count')]);
        else
            return response()->json(['count' => 0]);
    }
    public static function addToCart(Request $request){
        $article_id=$request->request->get('article_id');
        $article = Article::where('id',$article_id)
                            ->first();
        $count=0;
        if($article){
            //add count
            if($request->session()->has('cart_count'))
                $count=(int)$request->session()->get('cart_count');
            $count=$count+1;
            $request->session()->put('cart_count',$count);    
            //add article to session
            $request->session()->push('cart_articles',$article);
            $message='Article added!';
        }
        else{
            $message="This article doesn't exist!";
        }
        $request->session()->save();
        return response()->json([
                                    'message'=>$message,
                                    'article_id'=>$article_id,
                                    'article_name'=>$article['name'],
                                    'count'=>$count
                                ]);
    }
    public static function removeFromCart(Request $request){
        //verifying in database
        $article_id=$request->request->get('article_id');
        $article = Article::where('id',$article_id)
                            ->first();
        //if it exists in database
        if($article){
            //verify in session
            $articles_array = $request->session()->pull('cart_articles',[]);
            if(($key = array_search($article,$articles_array)) !== false){
                //removing from array
                unset($articles_array[$key]);
                //decremente count
                if($request->session()->has('cart_count')){
                    $count=$request->session()->get('cart_count');
                    $count=$count-1;
                    $request->session()->put('cart_count',$count);  
                }
                $request->session()->put('cart_articles', $articles_array);
                $message='Article removed successfully!';
            }
            //if not,nothing happens
            else{
                $message='Article not found in your cart!';
            }
        }
        else{
            $message="This article doesn't exist!";
        }
        $request->session()->save();
        return response()->json([
                                'message'=>$message,
                                'article_id'=>$article_id,
                                'article_name'=>$article['name']
                                ]);
    }
    public static function getAll(Request $request){
        return response()->json([
                               'articles'=>$request->session()->get('cart_articles')
                                ]);
    }
}