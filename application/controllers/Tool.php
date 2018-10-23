<?php
class Tool extends CI_Controller {

    public function index()
    {
        echo 'Hello World!';
    }

    public function gps()
    {
        $data['something'] = 'wahaha';
        $data['len_km'] = 10.1;
        $this->load->view("header", ['my_title'=>'经纬度算距离工具'] );
        $this->load->view("gps", $data);
        $this->load->view("footer");
    }

    public function calculate()
    {
        $something = $this->input->post('func');
        var_dump($something);
    }
}
