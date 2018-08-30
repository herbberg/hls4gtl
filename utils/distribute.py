#!/usr/bin/env python
# -*- coding: utf-8 -*-

from jinja2 import Environment, FileSystemLoader
from jinja2 import filters, StrictUndefined

import argparse
import datetime
import shutil
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

class Distribution(object):

    def __init__(self, templates_dir, filename):
        self.templates_dir = templates_dir
        hls_dir = os.path.join(templates_dir, 'hls')
        vhdl_dir = os.path.join(templates_dir, 'vhdl')
        self.engine = TemplateEngine([hls_dir, vhdl_dir])
        self.menu_name = os.path.basename(filename)

    def dist_dir(self, path, *args):
        filename = os.path.join(*args) if len(args) else ''
        return os.path.join(path, 'hls', 'module_0', 'src', 'impl', filename)

    def create_dirs(self, path, force):
        if os.path.isdir(path):
            if force:
                shutil.rmtree(path)
            else:
                raise RuntimeError("Distribution directory already exists: {}".format(path))
        if not os.path.isdir(path):
            os.makedirs(self.dist_dir(path))

    def write_template(self, template, filename, data):
        with open(filename, 'w') as fp:
            if not 'header_timestamp' in data:
                data['header_timestamp'] = datetime.datetime.now().isoformat()
            if not 'header_menu_name' in data:
                data['header_menu_name'] = self.menu_name
            content = self.engine.render(template, data)
            fp.write(content)

    def write_cuts(self, path):
        template = 'cuts.hxx'
        filename = self.dist_dir(path, template)
        data = {}
        self.write_template(template, filename, data)

    def write_conditions(self, path):
        template = 'conditions.hxx'
        filename = self.dist_dir(path, template)
        data = {}
        self.write_template(template, filename, data)

    def write_logic(self, path):
        template = 'logic.hxx'
        filename = self.dist_dir(path, template)
        data = {}
        self.write_template(template, filename, data)

    def write_symlink(self, path, name):
        root_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
        cwd = os.getcwd()
        os.chdir(root_dir)
        if os.path.exists(name):
            os.unlink(name)
        os.symlink(path, name)
        os.chdir(cwd)

    def write_impl(self, path, force=False):
        path = os.path.join(path, self.menu_name)
        self.create_dirs(path, force)
        self.write_cuts(path)
        self.write_conditions(path)
        self.write_logic(path)
        self.write_symlink(path, 'current_dist')


def parse_args():
    root_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
    default_templates_dir = os.path.join(root_dir, 'templates')
    default_output_dir = os.path.join(root_dir, 'dist')
    parser = argparse.ArgumentParser()
    parser.add_argument('filename', help="XML trigger menu")
    parser.add_argument('--templates', metavar='<dir>', default=default_templates_dir, help="template input directory")
    parser.add_argument('--output', metavar='<dir>', default=default_output_dir, help="distribution output directory")
    parser.add_argument('--force', action='store_true', help="force overwrite an exisiting distribution")
    return parser.parse_args()

def main():
    args = parse_args()

    dist = Distribution(args.templates, args.filename)
    dist.write_impl(args.output, args.force)

if __name__ == '__main__':
    main()
