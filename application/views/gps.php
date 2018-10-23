<script type="text/javascript">
function calculate()
{
    if ($("#a_lat").val() == "")
    {
        alert("A点经度为空");
    }
    $.post("calculate", { "a_lat": $("#a_lat").val() },
            function(data){
            alert(data.len_km); // John
            }, "json");
}
</script>

<body>
<div style="padding: 50px 100px 10px;">
<form class="bs-example bs-example-form" role="form">

<div> 
<div class="input-group">
<span class="input-group-addon">A点经度</span>
<input type="number" class="form-control"  placeholder="0" id="a_lat">
</div>
<br>
<div class="input-group">
<span class="input-group-addon">A点纬度</span>
<input type="number" class="form-control" placeholder="0" >
</div>
<br>
<div class="input-group">
<span class="input-group-addon">B点经度</span>
<input type="text" class="form-control" placeholder="0">
</div>
<br>
<div class="input-group">
<span class="input-group-addon">B点纬度</span>
<input type="text" class="form-control" placeholder="0" >
</div>

</div>

<br>
<div>
<button type="button" class="btn btn-primary" onclick="calculate()">计算</button>
</div>
<br>
<div class="input-group">
<span class="input-group-addon">两点距离</span>
<input type="text" readonly class="form-control" placeholder="" value="<?php echo $len_km;?>">
<span class="input-group-addon">米</span>
</div>
<div class="input-group">
<span class="input-group-addon">两点距离</span>
<input type="text" readonly class="form-control" placeholder="" value="<?php echo $len_km;?>">
<span class="input-group-addon">公里</span>
</div>
<div class="input-group">
<span class="input-group-addon">两点距离</span>
<input type="text" readonly class="form-control" placeholder="" value="<?php echo $len_km;?>">
<span class="input-group-addon">英尺</span>
</div>
<div class="input-group">
<span class="input-group-addon">两点距离</span>
<input type="text" readonly class="form-control" placeholder="" value="<?php echo $len_km;?>">
<span class="input-group-addon">海里</span>
</div>
<div class="input-group">
<span class="input-group-addon">B相对A方位</span>
<input type="text" readonly class="form-control" placeholder="" value="<?php echo $len_km;?>">
<span class="input-group-addon">度</span>
</div>
<div class="input-group">
<span class="input-group-addon">B相对A方位</span>
<input type="text" readonly class="form-control" placeholder="" value="<?php echo $len_km;?>">
<span class="input-group-addon">弧度</span>
</div>
<div class="input-group">
<input type="text" class="form-control">
<span class="input-group-addon">.00</span>
</div>
<br>
<div class="input-group">
<span class="input-group-addon">$</span>
<input type="text" class="form-control">
<span class="input-group-addon">.00</span>
</div>
</form>
</div>

</body>
