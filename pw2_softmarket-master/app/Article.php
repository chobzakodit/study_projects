<?php 
namespace App;

use Illuminate\Database\Eloquent\Model;

class Article extends Model {

	protected $table = 'articles';

    protected $fillable = [];

    protected $dates = [];

    public static $rules = [
        // Validation rules
    ];

    // Relationships

}
