#!/usr/bin/env python
# -*- coding: utf-8 -*-

from jinja2 import Environment, FileSystemLoader
from jinja2 import filters, StrictUndefined

import argparse
import shutil
import sys, os

temp_cuts = """
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
"""
temp_conditions = """
        const ap_uint<1> cond_double_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,2,12>(double_eg_2_requ, eg);
        const ap_uint<1> cond_single_jet_1 = comb_cond<jet_obj_requ_t,jet_obj_t,1,12>(single_jet_2_requ, jet);
        const ap_uint<1> cond_triple_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,3,12>(triple_eg_2_requ, eg);
        const ap_uint<1> cond_triple_eg_2 = comb_cond<eg_obj_requ_t,eg_obj_t,3,12>(triple_eg_3_requ, eg);
        const ap_uint<1> cond_quad_eg_1 = comb_cond<eg_obj_requ_t,eg_obj_t,4,12>(quad_eg_1_requ, eg);
"""
temp_seeds = """
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_double_eg_1) << 0;
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_single_jet_1) << 1;
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_triple_eg_1) << 2;
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_triple_eg_2) << 3;
        algo |= static_cast<ap_uint<N_ALGORITHMS> >(cond_quad_eg_1) << 4;
"""

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

class Implementation(object):

    def __init__(self, templates_dir):
        self.templates_dir = templates_dir
        hls_dir = os.path.join(templates_dir, 'hls')
        vhdl_dir = os.path.join(templates_dir, 'vhdl')
        self.engine = TemplateEngine([hls_dir, vhdl_dir])

    def create_dirs(self, path, force):
        if os.path.isdir(path):
            if force:
                shutil.rmtree(path)
            else:
                raise RuntimeError("implementation directory already exists: {}".format(path))
        if not os.path.isdir(path):
            os.makedirs(os.path.join(path, 'hls'))
            os.makedirs(os.path.join(path, 'vhdl'))

    def write_template(self, template, filename, data):
        with open(filename, 'w') as fp:
            content = self.engine.render(template, data)
            fp.write(content)

    def write_cuts(self, path):
        filename = os.path.join(path, 'hls', 'cuts.h')
        data = {'cuts': temp_cuts}
        self.write_template('cuts.h', filename, data)

    def write_conditions(self, path):
        template = 'conditions.h'
        filename = os.path.join(path, 'hls', template)
        data = {}
        self.write_template(template, filename, data)

    def write_logic(self, path):
        template = 'logic.h'
        filename = os.path.join(path, 'hls', template)
        data = {
            'conditions': temp_conditions,
            'seeds': temp_seeds,
        }
        self.write_template(template, filename, data)

    def write_impl(self, path, force=False):
        self.create_dirs(path, force)
        self.write_cuts(path)
        self.write_conditions(path)
        self.write_logic(path)

def parse_args():
    root_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
    default_templates_dir = os.path.join(root_dir, 'templates')
    default_impl_dir = os.path.join(root_dir, 'impl')
    parser = argparse.ArgumentParser()
    parser.add_argument('filename', help="XML trigger menu")
    parser.add_argument('--templates', metavar='<dir>', default=default_templates_dir, help="template input directory")
    parser.add_argument('--impl', metavar='<dir>', default=default_impl_dir, help="implementation output directory")
    parser.add_argument('--force', action='store_true', help="force overwrite an exisiting implementation")
    return parser.parse_args()

def main():
    args = parse_args()

    impl = Implementation(args.templates)

    impl.write_impl(args.impl, args.force)

if __name__ == '__main__':
    main()
