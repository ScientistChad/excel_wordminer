<?php

class Miner{
    
    function __construct($file){
        $excelobj = PHPExcel_IOFactory::load($file);
        $this->excel = $excelobj;
        $this->sheet = $excelobj->getSheet(0);
        $this->highestRow = $this->sheet->getHighestRow();
        $this->highestColumn = $this->sheet->getHighestColumn();
    }
    
    // Function designed to extract row and column data from the established .xslx file
    function extract(){
        $datamine_row = $datamine_col = $header = array();
        $i = 0; $j = 0;
        
        // Groups all excel data by row
        for ($row = 1; $row <= $this->highestRow; $row++) {
            $rowData = $this->sheet->rangeToArray('A' . $row . ':' . $this->highestColumn . $row, null, true, false);
            if(empty($header)){
                $header=$rowData[0];
            }else{
                for($col=0;$col<count($header);$col++){
                    $datamine_row[$i][$header[$col]] = $rowData[0][$col];                 
                }
                $i++;
            }
        }
        $this->data_row = $datamine_row;
        
        // Re-group all excel data by column
        foreach($datamine_row as $data){
            foreach($header as $grp){
                $datamine_col[$grp][$j] = $data[$grp];
            }
            $j++;
        }
        $this->data_col = $datamine_col;
    }
    
    
    // Function designed to parse a string and gather and count all word occurences
    function wordminer($str){
        include('include/stopwords.php');
        $mined = $results = $mined_data = array();
        $str = str_replace(array(',','"','(',')','.',"'"),'',$str);
        $mined = preg_split("/[\W,-]+/",strtolower($str));
        //$mined = str_replace(array(',','"','(',')','.',"'"),'',$mined);
        $mined = array_unique($mined);
        foreach($mined as $val){
            if(!in_array($val,$StopWords)){
                if(strlen($val)>2){
                    $tmp=substr_count($str, ' '. $val.' ');
                    if($tmp>2){
                        $results[$val]=$tmp;}}}}
                        arsort($results);
                        foreach($results as $key=>$val){
                            $abs=strtolower($key);
                            if(!in_array($key,$StopWords)){
                                $mined_data[$key]=$val;}}
                                return $mined_data;
    }
}





?>
