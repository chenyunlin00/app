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
        $a_lon = $this->input->post('a_lon');
        $a_lat = $this->input->post('a_lat');
        $b_lon = $this->input->post('b_lon');
        $b_lat = $this->input->post('b_lat');
        exec("./a.out 120 30 110 30", $ret);
        $len_km = $ret[0];
        $angle = $ret[1];
        echo json_encode(['code'=>0, 'msg'=>'',
            'data'=>['len_km'=>$len_km, 'angle'=>$angle]
            ]);
    }
}
