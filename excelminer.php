<?php
header("Content-type: text/plain");

// This requires the PHPExcel library to function properly
require('PHPExcel/Classes/PHPExcel.php');
include('miner.inc');

// Declare .xlsx file to mine
$file = "";

// Establish miner
$mine = new Miner($file);

// Extract data from .xlsx file
$mine->extract();

// Parse out data and count word occurence 
$parsed_data = array();
foreach($mine->data_col as $key=>$data){
    $parsed_data[$key] = $mine->wordminer(implode(' ',$data));    
}

// Print out example of retrieved data
print_r($parsed_data);


?>
