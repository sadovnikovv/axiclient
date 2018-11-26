/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */




int process(){

    List<VARS> var_list = get_var_list();
    
    List<BACK_VARS> back_list = process_json_request(var_list);
    
    set_var_list(back_list);

}