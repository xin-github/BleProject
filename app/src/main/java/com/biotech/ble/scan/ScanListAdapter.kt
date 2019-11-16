package com.biotech.ble.scan

import android.graphics.Color
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.biotech.ble.R
import com.biotech.blelib.adapter.DiscoveredBluetoothDevice

/**
 * @author TuXin
 * @date 2019-08-23 08:40.
 *
 * Email : tuxin@pupupula.com
 */
class ScanListAdapter(val act: ItemClickListener<DiscoveredBluetoothDevice>) : ListAdapter<DiscoveredBluetoothDevice, RecyclerView.ViewHolder>(DiffCallback()) {
    val mData = mutableListOf<DiscoveredBluetoothDevice>()
    var mFilterStr: String = ""
    var mShowAllDevice = true

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_scan_ble, parent, false)
        val viewHolder = ItemViewHolder(view)
        viewHolder.findViews()
        return viewHolder
    }

    fun setFilterString(str: String) {
        mFilterStr = str
        setDatas(mData)
    }

    fun setDatas(list: List<DiscoveredBluetoothDevice>) {
        val filterList =
                if (mShowAllDevice) {
                    list.filter {
                        it.name != null
                    }
                } else {
                    list.filter {
                        (it.name != null && it.name.startsWith("LL") || it.name.startsWith("LB")) && it.name.contains(mFilterStr)
                    }
                }

        val listSorted = filterList.sortedBy {
            it.name
        }

        submitList(listSorted)
        mData.clear()
        mData.addAll(listSorted)
    }

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        val data = getItem(position)
        holder.itemView.setTag(R.id.tag_ble, data)
        (holder as ItemViewHolder).mTvName.text = data.name
        holder.itemView.setOnClickListener {
            val value = it.getTag(R.id.tag_ble) as? DiscoveredBluetoothDevice
            if (value != null) {
                act.onItemClick(value)
            }
        }
    }


    private class DiffCallback : DiffUtil.ItemCallback<DiscoveredBluetoothDevice>() {
        override fun areItemsTheSame(oldItem: DiscoveredBluetoothDevice, newItem: DiscoveredBluetoothDevice): Boolean {
            return oldItem == newItem
        }

        override fun areContentsTheSame(oldItem: DiscoveredBluetoothDevice, newItem: DiscoveredBluetoothDevice): Boolean {
            return false
        }
    }

    class ItemViewHolder(val view: View) : RecyclerView.ViewHolder(view) {
        lateinit var mTvName: TextView
        fun findViews() {
            mTvName = view.findViewById(R.id.tvBleName)
        }
    }

}