<?php

$host="localhost";
$dbusername="root";
$dbpassword="";
$dbname="FOHOR_MALAI";

$conn=new PDO('mysql:host='.$host.';dbname='.$dbname,$dbusername,$dbpassword);

if(mysqli_connect_error())
{
  die('Connect Error ('. mysqli_connect_errorno().')'
  .mysqli_connect_error());
}

else {
  $RNAME=filter_input(INPUT_POST,'RE_NAME');

  $query2 = "DELETE FROM RLOCATION
            WHERE RLOCATION.RNAME = '$RNAME'";


             if($conn->query($query2)){
                 echo "Deleted Retailer Location";
             }
             else{
                 echo "Error: ". $query2."
                 ".$conn->error;
               }
     }

$conn = null;

?>

</br><button class="button"><a href = "home.php">Home </a></button>
