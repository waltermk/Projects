<html>
<head>
<title> Update Product Type </title>
<link rel="stylesheet" href="Query.css"
</head>
<body>
  <div class="card">
  <form method="post" action ="update.controller.php">
  <fieldset>

  <legend> Update SKU </legend>
      <label id= "label" for =""> Enter SKU </label> </br>
      <input style="width:200px;font-size:14pt;" type="text" name="SKU" placeholder="SKU" required > </br></br>

      <label id= "label" for =""> What would you set the type to </label> </br>
      <input style="width:200px;font-size:14pt;" type="text" name="NEWTYPE" placeholder="NEWTYPE" required> </br></br>

   <input id="button" type="submit" name="submit">
   <button class="button"><a href = "home.php">Home </a></button>

 </fieldset>
</form>
</div>
</body>
</html>
