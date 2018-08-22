import sys, os
import argparse

class BasicParser(object):

    def __init__(self, iterable):
        self._iterable = iterable
        self._lineno = 0
        self._line = ''

    def next(self):
        self._line = self._iterable.next().strip()
        self._lineno += 1

    @property
    def lineno(self):
        return self._lineno

    @property
    def line(self):
        return self._line

class TransactionParser(BasicParser):

    RUNTIME_BEGIN = '[[[runtime]]]'
    RUNTIME_END = '[[[/runtime]]]'
    TRANS_BEGIN = '[[transaction]]'
    TRANS_END = '[[/transaction]]'

    def __init__(self, iterable):
        super(TransactionParser, self).__init__(iterable)
        self.transactions = []
        self.current_index = None # to detect index jumps

    def append(self):
        if self.current_index != len(self.transactions):
            raise ValueError("line {} detected index jump, expected {}, got {}".format(self.lineno, len(self.transactions), self.current_index))
        self.transactions.append(int(self.line.strip(), 16))

    def raise_error(self, expected):
        raise RuntimeError("line {}, expected {}, got {}".format(self.lineno, expected, self.line))

    def parse_any(self, *parsers):
        errors = []
        for parser in parsers:
            try:
                return parser()
            except RuntimeError as e:
                errors.append(e)
        if len(errors) >= len(parsers):
            raise errors[-1]

    def parse_transaction_end(self):
        if self.line == self.TRANS_END:
            self.next()
            self.parse_any(
                self.parse_transaction_begin,
                self.parse_runtime_end,
            )
            return
        self.raise_error(self.TRANS_END)

    def parse_transaction_value(self):
        if self.line.startswith('0x'):
            if self.current_index != len(self.transactions):
                raise ValueError("line {} detected index jump, expected {}, got {}".format(self.lineno, len(self.transactions), self.current_index))
            self.append()
            self.next()
            self.parse_any(self.parse_transaction_end)
            return
        self.raise_error("expected hex value")

    def parse_runtime_end(self):
        if self.line != self.RUNTIME_END:
            self.raise_error(self.RUNTIME_END)

    def parse_transaction_begin(self):
        if self.line.startswith(self.TRANS_BEGIN):
            self.current_index = int(self.line.strip().split()[1].strip())
            self.next()
            self.parse_any(self.parse_transaction_value)
            return
        self.raise_error(self.TRANS_BEGIN)

    def parse_runtime_begin(self):
        if self.line == self.RUNTIME_BEGIN:
            self.next()
            self.parse_any(
                self.parse_transaction_begin,
                self.parse_runtime_end,
            )
            return
        self.raise_error(self.RUNTIME_BEGIN)

    def parse(self):
        self.next()
        self.parse_any(self.parse_runtime_begin)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('filename')
    return parser.parse_args()

if __name__ == '__main__':
    args = parse_args()
    with open(args.filename) as f:
        parser = TransactionParser(f)
        parser.parse()
        for transaction in parser.transactions:
            print("0x{:x}".format(transaction))
    sys.exit()
