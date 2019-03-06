<?php 
namespace App;

use Illuminate\Database\Eloquent\Model;

class Category extends Model {

	protected $table = 'categories';
	
    protected $categories = [];

    protected $dates = [];

    public static $rules = [
        // Validation rules
    ];
    public static function getAllCategoriesById($category_id){
        $c_path=Category::find($category_id);

        $c_path=$c_path['path'];
        $categories = Category::select('name')
                        ->where('path','like',"$c_path%")
                        ->get();
        return $categories;
    }
}
