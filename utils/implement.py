#!/usr/bin/env python
# -*- coding: utf-8 -*-

from jinja2 import Environment, FileSystemLoader
from jinja2 import filters, StrictUndefined

import argparse
import sys, os

CustomFilters = {}

class TemplateEngine(object):
    """Custom tempalte engine class."""

    def __init__(self, searchpath, encoding='utf-8'):
        # Create Jinja environment.
        loader = FileSystemLoader(searchpath, encoding)
        self.environment = Environment(loader=loader, undefined=StrictUndefined)
        self.environment.filters.update(CustomFilters)

    def render(self, template, data={}):
        template = self.environment.get_template(template)
        return template.render(data)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('filename', help="XML trigger menu")
    return parser.parse_args()

def main():
    args = parse_args()

    root_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
    impl_path = os.path.join(root_path, 'impl')
    tempalte_path = os.path.join(root_path, 'utils', 'templates', 'impl')

    engine = TemplateEngine(tempalte_path)

    if not os.path.isdir(impl_path):
        os.makedirs(impl_path)

    with open(os.path.join(impl_path, 'const.h'), 'w') as fp:
        data = {
            'cuts': """
const eg_obj_requ_t double_eg_2_requ[2] = {
    {.n_requ=2,.n_obj=12,.pt=10,.eta={{0x00BA,0x008D},{0x0072,0x0045},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0},
    {.n_requ=2,.n_obj=12,.pt=20,.eta={{0x0072,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{0,0},{0,0}},.n_phi=0},
};

const jet_obj_requ_t single_jet_2_requ[1] = {
    {.n_requ=1,.n_obj=12,.pt=10,.eta={{0x00BA,0x008D},{0x005B,0x002E},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0}
};

const eg_obj_requ_t triple_eg_2_requ[3] = {
    {.n_requ=3,.n_obj=12,.pt=10,.eta={{0x00BA,0x008D},{0x0072,0x0045},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0},
    {.n_requ=3,.n_obj=12,.pt=20,.eta={{0x0072,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{0,0},{0,0}},.n_phi=0},
    {.n_requ=3,.n_obj=12,.pt=10,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=0,.phi={{0,0},{0,0}},.n_phi=0}
};

const eg_obj_requ_t triple_eg_3_requ[3] = {
    {.n_requ=3,.n_obj=12,.pt=25,.eta={{0x00BA,0x008D},{0x0072,0x0045},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0},
    {.n_requ=3,.n_obj=12,.pt=15,.eta={{0x0072,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{0,0},{0,0}},.n_phi=0},
    {.n_requ=3,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=0,.phi={{0,0},{0,0}},.n_phi=0}
};

const eg_obj_requ_t quad_eg_1_requ[4] = {
    {.n_requ=4,.n_obj=12,.pt=11,.eta={{0x00BA,0x008D},{0x0072,0x0045},{0,0},{0,0},{0,0}},.n_eta=2,.phi={{0,0},{0,0}},.n_phi=0},
    {.n_requ=4,.n_obj=12,.pt=11,.eta={{0x0072,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=1,.phi={{0,0},{0,0}},.n_phi=0},
    {.n_requ=4,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=0,.phi={{0,0},{0,0}},.n_phi=0},
    {.n_requ=4,.n_obj=12,.pt=11,.eta={{0,0},{0,0},{0,0},{0,0},{0,0}},.n_eta=0,.phi={{0,0},{0,0}},.n_phi=0},
};
""",
        }
        content = engine.render('const.h', data)
        fp.write(content)

    with open(os.path.join(impl_path, 'logic.h'), 'w') as fp:
        data = {
            'conditions': """
        const ap_uint<1> cond_double_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,2,12>(double_eg_2_requ, eg);
        const ap_uint<1> cond_single_jet_1 = comb_cond<jet_obj_requ_t,jet_obj_t,1,12>(single_jet_2_requ, jet);
        const ap_uint<1> cond_triple_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,3,12>(triple_eg_2_requ, eg);
        const ap_uint<1> cond_triple_eg_2 = comb_cond<eg_obj_requ_t,eg_obj_t,3,12>(triple_eg_3_requ, eg);
        const ap_uint<1> cond_quad_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,4,12>(quad_eg_1_requ, eg);
""",
            'algorithms': """
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_double_eg_1) << 0;
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_single_jet_1) << 1;
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_triple_eg_1) << 2;
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_triple_eg_2) << 3;
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_quad_eg_1) << 4;
""",
        }
        content = engine.render('logic.h', data)
        fp.write(content)

if __name__ == '__main__':
    main()
