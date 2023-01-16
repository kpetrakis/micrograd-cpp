import torch
import struct

def test_sanity_check():

	x = torch.tensor([-4.0]).float()
	x.requires_grad = True

	z = 2 * x + 2 + x
	q = z.relu() + z * x
	h = (z * z).relu()
	y = h + q + q * x
	y.backward()
	xpt, ypt = x, y

	with open("test/sanity_check", "rb") as f:
		xmg_data, ymg_data, xmg_grad = struct.unpack('<3f',f.read())

# forward pass went well
	assert ymg_data == ypt.data.item()

# backward pass went well
	assert xmg_grad == xpt.grad.item()


def test_more_ops():

	a = torch.Tensor([-4.0]).float()
	b = torch.Tensor([2.0]).float()
	a.requires_grad = True
	b.requires_grad = True
	c = a + b
	d = a * b + b**3
	c = c + c + 1
	c = c + 1 + c + (-a)
	d = d + d * 2 + (b + a).relu()
	d = d + 3 * d + (b - a).relu()
	e = c - d
	f = e**2
	g = f / 2.0
	g = g + 10.0 / f
	g.backward()
	apt, bpt, gpt = a, b, g	
	
	with open("test/more_ops", "rb") as f:
		gmg_data, amg_grad, bmg_grad = struct.unpack("<3f", f.read())
	# print(gmg_data, amg_grad, bmg_grad)
	
	tol = 1e-4
	# forwarward pass went well
	assert abs(gmg_data - gpt.data.item()) < tol
	# backward pass went well
	assert abs(amg_grad - apt.grad.item()) < tol
	assert abs(bmg_grad - bpt.grad.item()) < tol


if __name__ == "__main__":

	test_sanity_check()
	test_more_ops()
