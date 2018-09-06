#!/usr/bin/env python

import argparse
import glob
import logging
import sys, os

MaxModules = 6
TargetSymlink = 'current_dist'

def colorize(text, style):
    """Colorize a text using TTY escape sequences.

    colorize('FOO', '1;34') # bold, blue text on TTY
    """
    if sys.stdout.isatty():
        return "\033[{}m{}\033[0m".format(style, text)
    return text

def integrity_check(path):
    """Check integrity of distribution (module) directory."""
    root_dir = os.path.join(path, '..', '..')
    if not os.path.isdir(root_dir):
        return False
    for name in ['hls', 'testvectors', 'vhdl', 'xml']:
        if not os.path.isdir(os.path.join(root_dir, name)):
            return False
    return True

def locate_testvectors(path):
    """Returns list of found testvectors and number of events."""
    testvectors = []
    for filename in glob.glob(os.path.join(path, 'TestVector*.txt')):
        with open(filename) as fp:
            events = sum(1 for line in fp)
        testvectors.append((filename, events))
    return testvectors

def cmd_clean(args):
    """Clear command, removes distribution symlink."""
    if os.path.islink(TargetSymlink):
        os.unlink(TargetSymlink)
        logging.info("removed symlink %s", TargetSymlink)

def cmd_init(args):
    """Init command, creates distribution symlink."""
    src_dir = os.path.join(args.dist, 'hls', 'module_{}'.format(args.module))
    if not os.path.isdir(src_dir):
        raise IOError("no such directory: {}".format(src_dir))
    if not integrity_check(src_dir):
        raise IOError("not a valid distribution directory: {}".format(src_dir))
    cmd_clean(args)
    logging.info("create symlink: current_dist -> %s", src_dir)
    os.symlink(src_dir, TargetSymlink)
    cmd_status(args)

def cmd_status(args):
    """Status command, shows integrity status of distribution symlink."""
    dirname = os.path.dirname
    basename = os.path.basename
    write = sys.stdout.write
    status = ('NOT_CONFIGURED', '1;33')
    if os.path.islink(TargetSymlink):
        target_dir = os.readlink(TargetSymlink)
        status = ('DEAD_SYMLINK', '1;31')
        if os.path.exists(target_dir):
            status = ('INVALID_LOCATION', '1;31')
            if integrity_check(target_dir):
                status = ('OK', '1;32')
                write("{}: {}\n".format(TargetSymlink, target_dir))
                module = basename(target_dir).split('_')[-1]
                write("module: {}\n".format(module))
                menu = basename(dirname(dirname((target_dir))))
                write("menu: {}\n".format(menu))
                testvectors_dir = os.path.join(target_dir, '..', '..', 'testvectors')
                testvectors = locate_testvectors(testvectors_dir)
                if testvectors:
                    write("testvectors: {}\n".format(len(testvectors)))
                    for filename, events in testvectors:
                        write(" - {} ({} events)\n".format(os.path.basename(filename), events))
                else:
                    write("testvectors: {}\n".format('none'))
    # add some fancy colors
    write("status: {}\n".format(colorize(*status)))

def parse_args():
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest='command')
    init_parser = subparsers.add_parser('init', help="initialize with module distribution")
    init_parser.add_argument('dist', help="menu distribution directory")
    init_parser.add_argument('module', type=int, help="module ID (0...{})".format(MaxModules-1))
    init_parser.set_defaults(func=cmd_init)
    clear_parser = subparsers.add_parser('clean', help="remove current module distribution")
    clear_parser.set_defaults(func=cmd_clean)
    status_parser = subparsers.add_parser('status', help="show module distribution")
    status_parser.set_defaults(func=cmd_status)
    return parser.parse_args()

def main():
    args = parse_args()
    logging.getLogger().setLevel(logging.INFO)
    args.func(args)
    sys.exit()

if __name__ == '__main__':
    main()
