<script type="text/javascript">
function calculate()
{
    var a_lat = 0;
    var a_lon = 0;
    var b_lat = 0;
    var b_lon = 0;
    if ($("#a_lat").val() != "")
    {
        a_lat = parseFloat($("#a_lat").val());
    }
    if ($("#a_lon").val() != "")
    {
        a_lon = parseFloat($("#a_lon").val());
    }
    if ($("#b_lat").val() != "")
    {
        b_lat = parseFloat($("#b_lat").val());
    }
    if ($("#b_lon").val() != "")
    {
        b_lon = parseFloat($("#b_lon").val());
    }
    $.post("calculate", 
            { 
                "a_lat" : a_lat,
                "a_lon" : a_lon,
                "b_lat" : b_lat,
                "b_lon" : b_lon
            },
            function(data){
                if (data.code != 0) {   
                    alert(data.msg);
                    return;
                }
                $("#len_km").val(data.data.len_km);
                $("#angle").val(data.data.angle);
            },
            "json"
            );
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
<input type="number" class="form-control" placeholder="0" id="a_lon">
</div>
<br>
<div class="input-group">
<span class="input-group-addon">B点经度</span>
<input type="number" class="form-control" placeholder="0" id="b_lat">
</div>
<br>
<div class="input-group">
<span class="input-group-addon">B点纬度</span>
<input type="number" class="form-control" placeholder="0" id="b_lon">
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
<input type="text" readonly class="form-control" placeholder="" id="len_km">
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
<input type="text" readonly class="form-control" placeholder="" id="angle">
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
