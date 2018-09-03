#ifndef REQUIREMENTS_H_
#define REQUIREMENTS_H_

#include "obj.h"

//     const eg_obj_req_t double_eg_2_req[2] = {
//         {.n_req=2,.n_obj=12,.pt=10,.eta={{-3,-5},{5,3},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{17,0},{0,0}},.n_phi=0},
//         {.n_req=2,.n_obj=12,.pt=20,.eta={{5,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{34,17},{0,0}},.n_phi=0},
//     };
//
//     const jet_obj_req_t single_jet_2_req[1] = {
//         {.n_req=1,.n_obj=12,.pt=10,.eta={{-3,-5},{4,2},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{17,0},{0,0}},.n_phi=0}
//     };
//
//     const eg_obj_req_t triple_eg_2_req[3] = {
//         {.n_req=3,.n_obj=12,.pt=10,.eta={{-3,-5},{5,3},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{17,0},{0,0}},.n_phi=0},
//         {.n_req=3,.n_obj=12,.pt=20,.eta={{5,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{34,17},{0,0}},.n_phi=0},
//         {.n_req=3,.n_obj=12,.pt=10,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{34,17},{0,0}},.n_phi=0}
//     };
//
//     const eg_obj_req_t triple_eg_3_req[3] = {
//         {.n_req=3,.n_obj=12,.pt=25,.eta={{-3,-5},{5,3},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{17,0},{0,0}},.n_phi=0},
//         {.n_req=3,.n_obj=12,.pt=15,.eta={{5,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{34,17},{0,0}},.n_phi=0},
//         {.n_req=3,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{34,17},{0,0}},.n_phi=0}
//     };
//
//     const eg_obj_req_t quad_eg_1_req[4] = {
//         {.n_req=4,.n_obj=12,.pt=11,.eta={{-3,-5},{5,3},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{17,0},{0,0}},.n_phi=0},
//         {.n_req=4,.n_obj=12,.pt=11,.eta={{5,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{34,17},{0,0}},.n_phi=0},
//         {.n_req=4,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{34,17},{0,0}},.n_phi=0},
//         {.n_req=4,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{34,17},{0,0}},.n_phi=0},
//     };

// 2018-08-20: converted eta values (like VHDL implementation)
    const eg_obj_req_t double_eg_2_req[2] = {
        {.n_req=2,.n_obj=12,.pt=10,.eta={{0x00BA,0x008D},{0x0072,0x0045},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0},
        {.n_req=2,.n_obj=12,.pt=20,.eta={{0x0072,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{0,0},{0,0}},.n_phi=0},
    };

    const jet_obj_req_t single_jet_2_req[1] = {
        {.n_req=1,.n_obj=12,.pt=10,.eta={{0x00BA,0x008D},{0x005B,0x002E},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0}
    };

    const eg_obj_req_t triple_eg_2_req[3] = {
        {.n_req=3,.n_obj=12,.pt=10,.eta={{0x00BA,0x008D},{0x0072,0x0045},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0},
        {.n_req=3,.n_obj=12,.pt=20,.eta={{0x0072,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{0,0},{0,0}},.n_phi=0},
        {.n_req=3,.n_obj=12,.pt=10,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=0,.phi={{0,0},{0,0}},.n_phi=0}
    };

    const eg_obj_req_t triple_eg_3_req[3] = {
        {.n_req=3,.n_obj=12,.pt=25,.eta={{0x00BA,0x008D},{0x0072,0x0045},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0},
        {.n_req=3,.n_obj=12,.pt=15,.eta={{0x0072,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{0,0},{0,0}},.n_phi=0},
        {.n_req=3,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=0,.phi={{0,0},{0,0}},.n_phi=0}
    };

    const eg_obj_req_t quad_eg_1_req[4] = {
        {.n_req=4,.n_obj=12,.pt=11,.eta={{0x00BA,0x008D},{0x0072,0x0045},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0},
        {.n_req=4,.n_obj=12,.pt=11,.eta={{0x0072,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{0,0},{0,0}},.n_phi=0},
        {.n_req=4,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=0,.phi={{0,0},{0,0}},.n_phi=0},
        {.n_req=4,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=0,.phi={{0,0},{0,0}},.n_phi=0},
    };

#endif
