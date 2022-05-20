/*
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2022 Loongson Technology Corporation Limited
 */

#include "base/ixgbe_common.h"
#include "ixgbe_ethdev.h"
#include "ixgbe_rxtx.h"

/* The vector support will come later */
int
ixgbe_rx_vec_dev_conf_condition_check(struct rte_eth_dev __rte_unused *dev)
{
	return -1;
}

uint16_t
ixgbe_recv_pkts_vec(
	void __rte_unused *rx_queue,
	struct rte_mbuf __rte_unused **rx_pkts,
	uint16_t __rte_unused nb_pkts)
{
	return 0;
}

uint16_t
ixgbe_recv_scattered_pkts_vec(
	void __rte_unused *rx_queue,
	struct rte_mbuf __rte_unused **rx_pkts,
	uint16_t __rte_unused nb_pkts)
{
	return 0;
}

int
ixgbe_rxq_vec_setup(struct ixgbe_rx_queue __rte_unused *rxq)
{
	return -1;
}

uint16_t
ixgbe_xmit_fixed_burst_vec(void __rte_unused *tx_queue,
		struct rte_mbuf __rte_unused **tx_pkts,
		uint16_t __rte_unused nb_pkts)
{
	return 0;
}

int
ixgbe_txq_vec_setup(struct ixgbe_tx_queue __rte_unused *txq)
{
	return -1;
}

void
ixgbe_rx_queue_release_mbufs_vec(struct ixgbe_rx_queue __rte_unused *rxq)
{
	return;
}
